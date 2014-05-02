## Introduction

This is simply a wrapper around the LLL compiler for the [CPP-Ethereum](https://github.com/ethereum/cpp-ethereum) client. This wrapper will allow you to assemble and compile LLL code with minimal difficulties.

## Installation

To Install this:

```bash
cd <CPP_ETHEREUM_DIR>
git clone git@github.com:ethereum-package-manager/lll-compiler.git compiler
cd compiler
cmake .
make
```

## Usage

ethcomp -asm FILE  -- to compile to assembly
ethcomp FILE       -- to compile to bytecode

## License

This is simply a wrapper around CPP-Ethereum's Intellectual Property, so this derivative work is licensed the same as the primary work.