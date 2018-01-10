import pathlib
import subprocess

pathlib.Path('./bin').mkdir(parents=True, exist_ok=True)
subprocess.run(["cmake", ".."], cwd="./bin")
subprocess.run(["make"], cwd="./bin")