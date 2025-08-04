Spelton
=================

A Static Checker for Memory-Related Bugs Triggered with C++ Smart Pointers

* [Download the Spelton Tool](https://github.com/SQUARE-RG/Spelton/releases/download/ASE-2021/spelton-x86_64-centos7-clang900-ase2021.tar.xz): (SHA256SUM 568c1a6e7573876ba75f614bb8956eb285729552a00a3dfc3214db3e23f69141)

* Download the benchmark in Table III
  - [Imitated Snippets](https://github.com/SQUARE-RG/Spelton/releases/download/ASE-2021/imitated.tar.xz): (SHA256SUM 5e7e5d74a50d67385e9c7c01b7df3eaba5e90c3bdd9c3b8e3a92897ad4b88945)
  - [Mutated Snippets](https://github.com/SQUARE-RG/Spelton/releases/download/ASE-2021/mutated.tar.xz): (SHA256SUM fae86aa471b81a4a93960ab205d3c035e109b8418aa5e69854ef9f813a7974d7)

* [Download the generator for imitated snippets](https://github.com/SQUARE-RG/Spelton/releases/download/ASE-2021/generator-of-imitated-snippets.tar.xz): (SHA256SUM e72b56cdf56d4b9f41a67b6fc1f540f2995741cc4ae2741977d11931b8337395)
  - Source code of the generator is stored in sub-director [generator](https://github.com/SQUARE-RG/Spelton/tree/main/generator)

* The benchmark in Table IV:
  - https://github.com/zsiciarz/aquila              (commit: d5e3bde3c8d07678a95f225b657a7bb23d0c4730)
  - https://github.com/aria2/aria2                  (commit: 9d0a48ac8147c5e56402706d5c17efa8bf6340f2)
  - https://github.com/DigitalInBlue/Celero         (commit: 0d7b24d77216e3b99382a2be139b44a57d1771f6)
  - https://github.com/Qihoo360/evpp                (commit: 86764566277574c2b73f300479ca46709385b2bb)
  - https://github.com/Project-OSRM/osrm-backend    (commit: 15f0ca8ddaa35c5b4d93c25afa72e81e1fb40c3e)
  - https://github.com/corvusoft/restbed            (commit: 03f1f2391fc8cd00f599ea368e472f1455bd575c)
  - https://github.com/gabime/spdlog                (commit: 3dedb52163c4aa052dee61ea3de126c72faa02a8)
  - https://github.com/mysql/mysql-server           (commit: ee4455a33b10f1b1886044322e4893f587b319ed)
  - https://github.com/llvm-project/llvm            (commit: bbd4ebffd4a634a9256f5eb33b3cce06ade8d809, subproject: clang flang llvm mlir)

Installation
--------------

The Spelton tool is provided as a tarball.
The directory tree after extraction is shown below.

```
spelton/
├── bin/
│   ├── clang -> clang-9
│   ├── clang++ -> clang
│   ├── clang-9                 Clang executable
│   ├── clang-cl -> clang
│   ├── clang-cpp -> clang
│   ├── clang-extdef-mapping    External definition mapping generator
│   ├── driver                  Built-in scheduler for paralle analysis
│   ├── genidx                  Index generator for the report directory
│   └── spelton                 Spelton analyzer executable
└── lib/
    ├── clang/
    └── genidx/
```

The Spelton executable is compiled on the top of the Docker image of CentOS 7. It requires the Python interpreter and GNU Make for the execution of the analysis scheduler and the index generator.

Among the files, the executable script `driver` serves as a parallel execution driver, which is used for analyzing a project in parallel. The executable `genidx` is used to generate the index file `index.html` for the report output directory. We also provide the Clang 9.0.0 compiler compiled together with Spelton, in case of necessary.

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
$ driver [command] [VAR=value] [-j <nproc>]
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

**Note:** Due to the limitation of the Cross Translation Unit (CTU) analysis in Clang Static Analyzer, the `analyze` target will execute Spelton twice, one with CTU analysis enabled and another disabled. The report counting in the paper did not deduplicate the reports for the same problem generated by two executions, as the detailed paths of the two versions may be different.

Example Analysis Workflow
-------------------------

This chapter provides a recommended analysis workflow, using the MySQL and Aria2 projects mentioned in the Spelton tool paper as examples.

1. Obtain the code, preprocess the project, compile, and generate the compilation database.

   For projects configured with the CMake tool, users can generate the compilation database by adding the `-DCMAKE_EXPORT_COMPILE_COMMANDS=ON` parameter when executing the `cmake` program. For projects configured with the AutoMake tool, users can capture compilation parameters during the build process using the `bear` ([Build EAR](https://github.com/rizsotto/Bear)) tool to generate the compilation database. After configuring the project, it is recommended to build the project to ensure that files generated only during compilation are correctly created and to check for any compilation errors.

2. Generate the input file list.

   ```sh
   $ /path/to/driver genifl
   ```

   The generated list will be placed in the `input.ifl` file in the current directory. The list contains all source files involved in the compilation database. Users can manually edit the list after generation to adjust the files to be analyzed. Lines starting with `#` in the list are considered comments.

3. Analyze the code.

   ```sh
   $ /path/to/driver analyze IFL=./input.ifl
   ```

   Specify the input file list as the `input.ifl` file in the current directory, use the `clang-extdef-mapping` program to generate the CTU index file, and then use the analyzer executable program to analyze all the translation units on the list. After analysis, call the report index generation tool to generate an index for the report folder.

   If an error occurs during the generation of the CTU index file, users can re-execute the last step. In this case, the incomplete CTU index file will continue to be generated, and once it is completed, the code analysis will start. The code analysis process will not fail and will not produce errors, even if crashes occur during analysis. Please be patient during the last few files of the analysis, as it may take a long time to complete. After the analysis is finished, users can check the log to identify files where crashes occurred during analysis.
