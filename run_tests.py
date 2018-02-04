import pathlib
import subprocess
import os

pathlib.Path('./bin').mkdir(parents=True, exist_ok=True)
subprocess.run(["cmake", ".."], cwd="./bin", check=True)
subprocess.run(["make"], cwd="./bin", check=True)

test_folder = "test/lattests/good/"
# test_folder = "test/mrjp-tests/good/basic/"
for file in sorted(os.listdir(test_folder)):
    if file.endswith('.lat'):
        print (file, ":")
        subprocess.run(["bin/exec", test_folder+file], check=True)
        subprocess.run(["llvm-as", (test_folder+file).replace('.lat', '.ll')], check=True)
        subprocess.run(["llvm-link", '-o', (test_folder+file).replace('.lat', '.bc_final'),
                        (test_folder+file).replace('.lat', '.bc'), 'llvm_playground/runtime.bc'], check=True)
        with open((test_folder+file).replace('.lat', '.out'), 'w') as output:
            if os.path.isfile((test_folder+file).replace('.lat', '.input')):
                with open((test_folder+file).replace('.lat', '.input'), 'r') as input:
                    subprocess.run(['lli', (test_folder+file).replace('.lat', '.bc_final')], stdin=input, stdout=output, check=True)
            else:
                subprocess.run(['lli', (test_folder+file).replace('.lat', '.bc_final')], stdout=output, check=True)
        subprocess.run(['diff',  '-q', (test_folder+file).replace('.lat', '.out'), (test_folder+file).replace('.lat', '.output')])
        subprocess.run(["rm", (test_folder+file).replace('.lat', '.bc_final'), (test_folder+file).replace('.lat', '.bc')])
        print()
