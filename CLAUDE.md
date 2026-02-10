# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

CTR-ModSDK is a toolkit for creating mods for Crash Team Racing (1999) on PlayStation 1, combined with an ongoing **non-matching decompilation** effort to reverse-engineer CTR from assembly to C.

The decompilation uses the **Ship of Theseus** strategy: leveraging PCSX-Redux's 8MB memory expansion, decompiled functions are loaded into memory alongside the original game, allowing direct comparison of outputs between original and decompiled versions.

## Build Commands

**Decompile project** (gcc 13.1/2):
```bash
cd decompile
./build.bat  # Choose: Compile → Build ISO → test
```

**Rewrite project** (gcc 15.2):
```bash
cd rewrite
./build.bat
```

Switch GCC versions with `mips` or `mips use <version>` command.

## Architecture

### Directory Structure
- `decompile/` - Legacy decompilation (500+ functions). Lower quality, monolithic headers, replaces original functions in-place. Organized by game system in `General/`.
- `rewrite/` - Modern rewrite with higher standards: unit testing, modular headers (`include/ctr/`), and loads new functions into high memory (0x80400000+) while patching callsites rather than replacing originals.
  - `src/exe/` - Decompiled functions
  - `src/tests/` - Test harnesses comparing decompiled vs original output
  - `src/hooks/dll/` - Boot loader
- `include/ctr/` - Modular headers for rewrite (preferred over monolithic `include/common.h`)
- `ghidra/` - Annotated disassembly (~90% of game)
- `symbols/` - Address mappings per region (gcc-syms*.txt)
- `mods/` - Finished mods (Patches, Modules, Standalones, etc.)

### Supported Versions
| Build ID | Version |
|----------|---------|
| 926 | USA Retail (ntsc-u) |
| 1020 | Europe Retail (pal) |
| 1111 | Japan Retail (ntsc-j) |
| 903 | Sept 3 Prototype |
| 1006 | Japan Trial |
| 9999 | Rewrite module |

The primary/focus version for decompile is 926, the only version being focused on for the rewrite is 926.

### Testing Framework (rewrite/)
Each decompiled function requires:
1. Entry in `s_functions` table at `src/tests/test.c`
2. A `TEST_*` function that:
   - Restores state before the decompiled call
   - Patches game to call original function
   - Compares original vs decompiled output
3. For functions using globals: a `BACKUP_*` function to store state

**Naming conventions differ between projects:**
- `rewrite/`: Original functions use `ND_` prefix (e.g., `ND_MATH_Sin`), decompiled versions have no prefix (`MATH_Sin`)
- `decompile/`: Original functions have no prefix, decompiled versions use `DECOMP_` prefix (e.g., `DECOMP_MATH_Sin`)

### Code Organization Patterns
- Overlay numbers (221-233) represent different game modules loaded dynamically
- Function naming: `SYSTEM_##_FunctionName` (e.g., `MATH_0_Sin`, `COLL_02_FIXED_BSPLEAF_TestInstance`)
- Headers in `include/ctr/` mirror the source organization
- Symbol files link decompiled code to original addresses

## Key Files
- `config.json` - Compiler settings and version mappings
- `symbols/gcc-syms-rewrite.txt` - Original function addresses for rewrite
- `symbols/gcc-extern-rewrite.txt` - External global variable addresses
- `include/common.h` - Precompiled header (~12MB)

## References
- **GTE (Geometry Transformation Engine)**: For questions about the PS1's math coprocessor, see https://psx-spx.consoledev.net/geometrytransformationenginegte/
