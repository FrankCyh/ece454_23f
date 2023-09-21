# This is the tester which is used to mark your ECE454-Lab4
import os
import shutil
import subprocess
import signal
import filecmp

import pathlib
os.chdir(os.path.dirname(os.path.realpath(__file__)))       # change to the directory script is in
scriptDir = os.path.dirname(os.path.realpath(__file__))     # store the script directory into a variable

# This tester has the following assumptions
# - gol.tar.gz containing student's solution is placed in the same working directory as the autotester.py script
# - after extracting the autotester into temporary directory named gol, there should be a folder called src
#   - a make file compiling the code must exist in gol/src
#   - i.e. gol.tar.gz -C gol, cd gol/src, make needs to work
# - after compiling, an executable must be made in the root decompressed directory
#   - i.e.   /usr/bin/time -f "%e real" ./gol/src/gol 10000 /input/1k.pbm results/1k.pbm
# - student's solution must pass the the verification by comparing against the official result
#   - i.e. diff 1k_verify_out.pbm 1k.pbm needs to be the same
# We set a timeout of 5 minute for each solution (very generous - 2x the unoptimized code)

runtime_studentSolution = -1
runtime_base = 191.26   # server's performance
# runtime_base = xxx    # ug machine's performance
speedup = 0

output_log = []

if not os.path.exists(scriptDir + '/gol.tar.gz'):
    output_log = ['GOL solution is invalid']
    for line in output_log:
        print(line.strip())
else:
    # Step 1 - remove previous gol if exist
    if os.path.exists(scriptDir + '/gol'):
        shutil.rmtree(scriptDir + '/gol')

    # Step 2 - create a gol directory
    if not os.path.exists(scriptDir + '/gol'):
        os.makedirs(scriptDir + '/gol')

    # Step 3 - decompress student's gol.tar.gz into the gol directory
    # assume always reliable, no error handling
    output_log += ['****Decompression Logs: *****************************************************']
    parameterList = ['tar', '-xvf', 'gol.tar.gz', '-C', 'gol']
    proc = subprocess.Popen(parameterList, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, preexec_fn=os.setsid)  # redirect stderr to stdout
    stdout, stderr = proc.communicate()    # no timeout on this one, assume 100% reliable
    output_log += stdout.decode('utf-8').split("\n")
    for line in output_log:
        print(line.strip())

    # Step 4 - make the program
    output_log = ['****Compilation Logs: *****************************************************']

    parameterList = ['make', 'clean']
    proc = subprocess.Popen(parameterList, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, preexec_fn=os.setsid, cwd=scriptDir+'/gol/src')  # redirect stderr to stdout
    stdout, stderr = proc.communicate()    # no timeout on this one, assume 100% reliable
    output_log += stdout.decode('utf-8').split("\n")
    for line in output_log:
        print(line.strip())

    parameterList = ['make']
    proc = subprocess.Popen(parameterList, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, preexec_fn=os.setsid, cwd=scriptDir+'/gol/src')  # redirect stderr to stdout
    stdout, stderr = proc.communicate()    # no timeout on this one, assume 100% reliable
    output_log += stdout.decode('utf-8').split("\n")
    for line in output_log:
        print(line.strip())

    # Step 4b - clean up the outputs folder
    #   - remove everything but 1k_verify_out.pbm
    for root, dirs, filenames in os.walk(scriptDir + '/gol/src/outputs'):
        # remove top level files
        for fileName in filenames:
            if fileName != '1k_verify_out.pbm':
                os.remove(scriptDir + '/gol/src/outputs/' + fileName)
        # remove all top level folders
        for folderName in dirs:
            shutil.rmtree(scriptDir + '/gol/src/outputs/' + folderName)
        break   # not recursive

    # Step 5 - runs the application and record time
    # assumes user do not modify inputs folder
    output_log = ['****Execution and Instrumentation Logs: *****************************************************']
    parameterList = ['/usr/bin/time', '-f', '"%e real"', './gol', '10000', 'inputs/1k.pbm', 'outputs/1k.pbm']
    try:
        # Run benchmark suite for 5 minutes
        timeoutSeconds = 60*5
        proc = subprocess.Popen(parameterList, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, preexec_fn=os.setsid, cwd=scriptDir+'/gol/src')
        stdout, stderr = proc.communicate(timeout=timeoutSeconds)
        output_log += stdout.decode('utf-8').split("\n")
        # assuming time returns the time on the last line, obtain the student's solution run time
        runtime_studentSolution = float(stdout.decode('utf-8').split("\n")[-2].replace('"', '').split(" ")[0])
    except subprocess.TimeoutExpired as exc:
        os.killpg(os.getpgid(proc.pid), signal.SIGTERM)
        stdout, stderr = proc.communicate()
        output_log += stdout.decode('utf-8').split("\n") + ['Solution terminated/timed out after 30min']
    for line in output_log:
        print(line.strip())

    # Step 6 - verifies output for correctness
    output_log = ['****Output Verification Logs: *****************************************************']
    with open(scriptDir + '/gol/src/teamInfo.txt') as f:
        output_log += list(f)
    try:
        if (filecmp.cmp(scriptDir+'/gol/src/outputs/1k_verify_out.pbm', scriptDir+'/gol/src/outputs/1k.pbm')):
            # it is the same, calculate the speedup
            speedup = str(round((runtime_base / runtime_studentSolution), 2))
            output_log += ['GOL Speedup: ' + speedup]
        else:
            output_log += ['Solution output failed verification']
            output_log += ['GOL Speedup: 0']
    except Exception as e:
        output_log += ['Solution output failed verification: Please do not remove ik_verify_out.pbm']
        output_log += ['GOL Speedup: 0']

    for line in output_log:
        print(line.strip())
