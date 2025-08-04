Spelton
=================

A Static Checker for Memory-Related Bugs Triggered with C++ Smart Pointers

[Download the Spelton Tool](#)
(SHA256SUM b12f5c3f47b662a79cbe5f17452019eb44c3134b0219d572d9f1b112de6a71ae)

Installation
--------------

The Spelton tool is provided as a tarball.
The directory tree after extraction is shown below.

```
spelton/
|---- analyze.makefile*
|---- genidx/
|     `---- genidx.py*
|---- resources/
|---- clang-extdef-mapping*
`---- spelton*
```

Among the files, the executable script `analyze.makefile` serves as a parallel execution driver, which can be used for parallel analysis of multiple files. The contents of the folder `genidx` include tools and resources needed to generate the report's index file `index.html`, with the executable script `genidx.py` being the actual tool used to generate the index. The folder `resources` contains resource files required by the compiler front-end, and the executable program `spelton` is the tool itself.

The executable program `spelton` for the tool is compiled on Ubuntu 20.04 system without any additional software dependencies. Users only need to install Python 2 and GNU Make for script execution.

Analyzing Code with the Tool Executable
---------------------------

The command-line arguments that Spelton accepts and their usages are presented as follows.

Command-line format:
```sh
$ /path/to/spelton [options] <source0> [... <sourceN>] [-- <compilation arguments>]
```

The `[options]` part can specify the following options:

Spelton Options:
- `--ctu=<string>`: Specify the path to the CTU index file (use `-ctu=/path/to/externalFnMap.txt` to specify the index file, or use `-ctu=` to disable CTU analysis).
- `--target=<string>`: Analyze only functions with the specified function signatures.

Analyzer Options:
- `--diag-cli=<value>`: Specify the format of output reports.
  - `html` (default): HTML report.
  - `plist`: PList report.
  - `text`: Print report information directly to the console.
- `--extra-arg=<string>`: Additional arguments to append after the arguments provided by the compilation database.
- `--extra-arg-before=<string>`: Arguments to insert before the arguments provided by the compilation database.
- `-p=<string>`: Path to the compilation database.

Other Options:
- `--help`: Display help information.
- `--version`: Display version information.

In addition to adding extra compilation command-line arguments on top of the compilation database using `-extra-arg` and `-extra-arg-before`, users can also provide the compiler arguments directly at the end of the command line using the `--` delimiter. For more detailed information on [Clang Tooling](https://releases.llvm.org/9.0.0/tools/clang/docs/HowToSetupToolingForLLVM.html) and [compilation database](https://releases.llvm.org/9.0.0/tools/clang/docs/JSONCompilationDatabase.html), please refer to the Clang documentation.

Concurrent Analysis with the Driver
----------------------------------------

Command-line format:
```sh
$ analyze.makefile [command] [VAR=value] [-j <nproc>]
```

The `[command]` part specifies the following functionalities:
- `analyze`: Perform analysis.
- `index`: Generate only the bug report index `index.html`.
- `exfnmap`: Generate only the CTU index file.
- `genifl`: Generate the analysis input file list using the compilation database.
- `archive`: Archive the last analysis report and log (rename these two folders with timestamps).
- `sources`: Print the list of input files being analyzed.
- `logs`: Print the list of log files.
- `dump`: View the analysis log using the `less` command.
- `help`: Display help information (this is the default action when no parameters are provided).
- `helpexe`: Display help information for the Spelton executable program.

The variable definitions `[VAR=value]` can include the following variables:
- `IFL`: Specify the input file list.
- `OUT`: Specify the output path for log files (default is `scan-dir`).

Since this script is a makefile, all command-line arguments of GNU Make are also valid, such as `-j` and `-k`.

Example Analysis Workflow
-------------------------

This chapter provides a recommended analysis workflow, using the MySQL and Aria2 projects mentioned in the Spelton tool paper as examples.

1. Obtain the code, preprocess the project, compile, and generate the compilation database.

   For projects configured with the CMake tool, users can generate the compilation database by adding the `-DCMAKE_EXPORT_COMPILE_COMMANDS=ON` parameter when executing the `cmake` program. For projects configured with the AutoMake tool, users can capture compilation parameters during the build process using the `bear` ([Build EAR](https://github.com/rizsotto/Bear)) tool to generate the compilation database. After configuring the project, it is recommended to build the project to ensure that files generated only during compilation are correctly created and to check for any compilation errors.

2. Generate the input file list.

   ```sh
   $ /path/to/analyze.makefile genifl
   ```

   The generated list will be placed in the `input.ifl` file in the current directory. The list contains all source files involved in the compilation database. Users can manually edit the list after generation to adjust the files to be analyzed. Lines starting with `#` in the list are considered comments.

3. Analyze the code.

   ```sh
   $ /path/to/analyze.makefile analyze IFL=./input.ifl
   ```

   Specify the input file list as the `input.ifl` file in the current directory, use the `clang-extdef-mapping` program to generate the CTU index file, and then use the analyzer executable program to analyze all the translation units on the list. After analysis, call the report index generation tool to generate an index for the report folder.

   If an error occurs during the generation of the CTU index file, users can re-execute the last step. In this case, the incomplete CTU index file will continue to be generated, and once it is completed, the code analysis will start. The code analysis process will not fail and will not produce errors, even if crashes occur during analysis. Please be patient during the last few files of the analysis, as it may take a long time to complete. After the analysis is finished, users can check the log to identify files where crashes occurred during analysis.	
	

