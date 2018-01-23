import pathlib
import subprocess
import os

pathlib.Path('./bin').mkdir(parents=True, exist_ok=True)
subprocess.run(["cmake", ".."], cwd="./bin", check=True)
subprocess.run(["make"], cwd="./bin", check=True)

test_folder = "test/lattests/good/"
for file in sorted(os.listdir(test_folder)):
    if file.endswith('.lat'):
        print (file, ":")
        subprocess.run(["bin/exec", test_folder+file], check=True)
        subprocess.run(["llvm-as", (test_folder+file).replace('.lat', '.ll')], check=True)
        subprocess.run(["llvm-link", '-o', (test_folder+file).replace('.lat', '.bc_final'),
                        (test_folder+file).replace('.lat', '.bc'), 'llvm_playground/runtime.bc'], check=True)
        # subprocess.run(['lli', (test_folder+file).replace('.lat', '.bc_final'), '-o', file.replace('.lat', '.out')], check=True)
        subprocess.run(["rm", (test_folder+file).replace('.lat', '.bc_final'), (test_folder+file).replace('.lat', '.bc')])
        print()
