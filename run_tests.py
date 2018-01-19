import pathlib
import subprocess
import os

pathlib.Path('./bin').mkdir(parents=True, exist_ok=True)
subprocess.run(["cmake", ".."], cwd="./bin", check=True)
subprocess.run(["make"], cwd="./bin", check=True)

test_folder = "test/lattests/bad/"
for file in sorted(os.listdir(test_folder)):
    if file.endswith('.lat'):
        print (file, ":")
        subprocess.run(["bin/exec", test_folder+file])
        print()
