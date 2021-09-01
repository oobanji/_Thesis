# How to run the DAP Binary Miner notebook


## Steps
* Run the `BMiner.ipynb` from the beginning up to the section `Subjects` to generate the file `dapserver.py` and `miner.py`.
* Next, run the `BinaryDebugServer.ipynb` to start the `debugserver.py`.
* Lastly, Execute the subsections under `Subjects` to generate the grammar for each subject.

Please **note** that if you experience a `Connection refused error` when derving grammar for each subjects, this is because the previous socket connection is still in use for running the `dapServer.py`. You can simply run `!kill -9 $(lsof -ti tcp:8541)` in the `BinaryDebugServer.ipynb` and re-run `!gdb --batch-silent -x dapServer.py` in the `BinaryDebugServer.ipynb` file.