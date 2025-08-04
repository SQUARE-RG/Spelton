#!/usr/bin/env python3

import os
import sys
from subprocess import Popen as popen
from subprocess import PIPE as pipe
from multiprocessing import Pool as pool


sys.dont_write_bytecode = True
opt = None


def ParseArgs(argv):
    import argparse
    parser = argparse.ArgumentParser(prog=argv[0],
                                     description='A naive template generator.')
    parser.add_argument('-t', '--templates', dest='templates', type=str,
                        help='Custom template directory.', required=True)
    parser.add_argument('-c', '--configures', dest='configures', type=str,
                        help='Custom configure directory.', required=True)
    parser.add_argument('-o', '--output', dest='output', type=str,
                        help='Custom output directory. (default ./output)',
                        default='./output')
    parser.add_argument('-q', '--quiet', dest='quiet', action='store_true',
                        help='Do not dump the process.', default=False)
    parser.add_argument('-j', '--jobs', dest='jobs', type=int,
                        help='Allow N jobs at once.', default=1)
    parser.add_argument('--format', dest='format', type=str,
                        help='Format output code. (default clang-format)',
                        default='clang-format')
    global opt
    opt = parser.parse_args(argv[1:])

    if not os.path.isdir(opt.templates):
        print("Error: Cannot open template directory.")
    if not os.path.isdir(opt.configures):
        print("Error: Cannot open configure directory.")
    if not os.path.isdir(opt.output) and os.path.exists(opt.output):
        print("Error: Output name is not a directory.")
    if opt.format:
        try:
            popen([opt.format, '--version'], stdout=pipe, stderr=pipe).wait()
        except FileNotFoundError:
            opt.format = ''

    return opt


def WriteFile(f, text):
    if opt.format:
        proc = popen([opt.format, '--style=LLVM'],
                     stdin=pipe, stdout=pipe, stderr=pipe)
        text = proc.communicate(input=text.encode())[0].decode()
        proc.wait()
    if not opt.quiet:
        print('Generating ' + os.path.basename(f.name))
    f.write(text)


def ReplacePtrsAndWrite(name, content):
    # print(name)

    ## If PTRs are not used, write to one file.
    from re import sub, search
    if not search(r'%MAKEPTR%|%SMARTPTR%', content):
        name = sub(r'%KIND%', 'all', name)
        with open(name, 'w') as f:
            WriteFile(f, content)
        return

    ## If PTRs are used, replace it with both unique and shared.
    unique_content = sub(r'%MAKEPTR%', 'make_unique', content)
    unique_content = sub(r'%SMARTPTR%', 'unique_ptr', unique_content)
    unique_name = sub(r'%KIND%', 'unique', name)
    with open(unique_name, 'w') as f:
        WriteFile(f, unique_content)

    shared_content = sub(r'%MAKEPTR%', 'make_shared', content)
    shared_content = sub(r'%SMARTPTR%', 'shared_ptr', shared_content)
    shared_name = sub(r'%KIND%', 'shared', name)
    with open(shared_name, 'w') as f:
        WriteFile(f, shared_content)


def GenerateOne(template, config, outputdir):
    # print(template, config, outputdir)

    ## read template:
    header_content =  ''.join([
        '// Template generated test case, do not edit!\n',
        '// template: ' + os.path.basename(template) + '\n',
        '// configure: ' + config[1] + '\n',
        '\n'
    ])
    template_content = open(template, 'r').read()
    template_content = header_content + template_content
    # print(template_content)

    ## check config:
    from importlib import import_module
    path = sys.path
    sys.path = [config[0]] + sys.path
    config_content = import_module(config[1])
    sys.path = path
    # print(dir(config_content))
    if not all(x in dir(config_content) \
               for x in ['TYPE', 'DESC', 'BADCODE', 'GOODCODE']):
        print("Error: invalid configure: " + config)
        return
    TYPE = config_content.TYPE
    DESC = config_content.DESC
    BADCODE = config_content.BADCODE
    GOODCODE = config_content.GOODCODE
    DEFINE = '/* No additional definitions from configure. */'
    PARAM = ''
    RETTYPE = 'void'
    try:
        DEFINE = config_content.DEFINE
    except AttributeError:
        pass
    try:
        PARAM = config_content.PARAM
    except AttributeError:
        pass
    try:
        RETTYPE = config_content.RETTYPE
    except AttributeError:
        pass

    ## generate output directory:
    outputdir = os.path.join(os.path.abspath(outputdir), config_content.TYPE)
    # print(outputdir)
    try:
        os.makedirs(outputdir)
    except FileExistsError:
        pass

    ## replace basic variables:
    from re import sub
    template_content = sub(r'%TYPE%', TYPE, template_content)
    template_content = sub(r'%DESC%', DESC, template_content)
    template_content = sub(r'%BADCODE%', BADCODE, template_content)
    template_content = sub(r'%GOODCODE%', GOODCODE, template_content)
    template_content = sub(r'%DEFINE%', DEFINE, template_content)
    template_content = sub(r'%PARAM%', PARAM, template_content)
    template_content = sub(r'%RETTYPE%', RETTYPE, template_content)
    # print(template_content)

    ## generate output filename template:
    outputname = os.path.join(
            outputdir,
            TYPE + '__' + DESC + '_%KIND%_' +
                sub(r'[^0-9]*([0-9]+)\.tmpl\.(.*)', r'\1.\2', template)
    )

    ## replace pointers and write to file:
    ReplacePtrsAndWrite(outputname, template_content)


def Generate():
    from fnmatch import fnmatchcase as match
    from re import sub
    configures = [
        (opt.configures, sub(r'(.*)\.py', r'\1', t)) \
        for r,d,f in os.walk(opt.configures) for t in f if match(t, '*.py')
    ]
    templates = [
        os.path.join(opt.templates, t) \
        for r,d,f in os.walk(opt.templates) for t in f if match(t, '*.tmpl.cc')
    ]
    # GenerateOne(templates[0], configures[0], opt.output)
    joblist = []
    for t in templates:
        for c in configures:
            joblist.append((t, c, opt.output))
    if opt.jobs == 1:
        for t,c,o in joblist:
            GenerateOne(t, c, o)
    else:
        with pool(opt.jobs) as p:
            p.starmap(GenerateOne, joblist)
    import shutil
    shutil.copy(os.path.join(opt.templates, 'std_testcase.cc'), opt.output)
    shutil.copy(os.path.join(opt.templates, 'std_testcase.h'), opt.output)
    shutil.copy(os.path.join(opt.templates, 'makefile'), opt.output)


def main():
    ParseArgs(sys.argv)
    Generate()


if __name__ == '__main__':
    main()
