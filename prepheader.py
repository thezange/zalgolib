#!/usr/bin/python3
from tempfile import NamedTemporaryFile
from os import rename
header = "zalgolib.h"
temp = header + "~"
with open(header) as f, open(temp, "w") as fout:
    fout.write("#ifndef ZALGOLIB__H\n")
    fout.write("#define ZALGOLIB__H\n")
    for line in f:
        if ("#include \"" not in line and
                "#ifndef" not in line and
                "#define" not in line and
                "#endif" not in line):
            fout.write(line)
    fout.write("#endif\n")
    rename(temp, header)

