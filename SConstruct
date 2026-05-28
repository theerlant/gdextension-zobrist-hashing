#!/usr/bin/env python
import os
import sys

env = SConscript("godot-cpp/SConstruct")

# Point the compiler to your source code
env.Append(CPPPATH=["src/"])
sources = Glob("src/*.cpp")
sources = [f for f in sources if f.name != "test.cpp"]

# Define the output library name and location
if env["platform"] == "macos":
    library = env.SharedLibrary(
        "bin/zobrist.{}.{}.framework/zobrist.{}.{}".format(
            env["platform"], env["target"], env["platform"], env["target"]
        ),
        source=sources,
    )
else:
    library = env.SharedLibrary(
        "bin/zobrist{}{}".format(env["suffix"], env["SHLIBSUFFIX"]),
        source=sources,
    )

Default(library)