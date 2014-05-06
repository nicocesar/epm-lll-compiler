## Introduction

This is simply a wrapper around the LLL compiler for the [CPP-Ethereum](https://github.com/ethereum/cpp-ethereum) client. This wrapper will allow you to assemble and compile LLL code with minimal difficulties.

## Installation

To Install this:

```bash
git clone git@github.com:ethereum-package-manager/epm-lll-compiler.git ethcomp
cd ethcomp
```

Then, update the CMAKE file line which says: `include_directories(/opt/cpp-ethereum)` to whereever your cpp-ethereum folder is located. Then.

```bash
cmake . && make
```

This will compile a `ethcomp` binary which you can place anywhere in your $PATH for easy compilation from scripts or otherwise. An example ruby script which uses the compiler is included as ethcompfix.

## Usage

* `ethcomp --asm FILE`  -- to compile to assembly
* `ethcomp FILE`        -- to compile to bytecode

## License

This is simply a wrapper around CPP-Ethereum's Intellectual Property, so this derivative work is licensed the same as the primary work.
