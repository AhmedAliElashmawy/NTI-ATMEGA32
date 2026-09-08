#!/usr/bin/env python3
import json
import os
import sys

def main():
    workspace = os.getcwd()
    srcs = sys.argv[1].split() if len(sys.argv) > 1 else []
    includes = sys.argv[2] if len(sys.argv) > 2 else ""
    cflags = sys.argv[3] if len(sys.argv) > 3 else ""
    compiler = sys.argv[4] if len(sys.argv) > 4 else "avr-gcc"

    entries = []
    for s in srcs:
        if not s.endswith(".c"):
            continue
        rel = os.path.normpath(s)
        abs_file = os.path.abspath(s)
        base = os.path.splitext(rel)[0]
        obj = os.path.join(workspace, "build", f"{base}.o")
        cmd = f"{compiler} {cflags} {includes} -c {s} -o {obj}"
        entries.append({
            "directory": workspace,
            "command": cmd,
            "file": abs_file
        })

    out_file = os.path.join(workspace, "compile_commands.json")
    with open(out_file, "w") as f:
        json.dump(entries, f, indent=2)

if __name__ == "__main__":
    main()
