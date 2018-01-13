import pathlib
import subprocess
import os

pathlib.Path('./bin').mkdir(parents=True, exist_ok=True)
subprocess.run(["cmake", ".."], cwd="./bin")
subprocess.run(["make"], cwd="./bin")

test_folder = "test/mrjp-tests/bad/semantic/"
for file in sorted(os.listdir(test_folder)):
    print (file, ":")
    subprocess.run(["bin/exec", test_folder+file])
    print()