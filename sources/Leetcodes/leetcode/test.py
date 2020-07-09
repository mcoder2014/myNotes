#!/usr/bin/python3
# -*- coding: UTF-8 -*- 

import os
import shutil

MAIN_CPP = "main.cpp"

folders = os.listdir(".")
print(folders)

# copy
for folder in folders:
    if folder[0] < '0' or folder[0] > '9':
        continue

    subFiles = os.listdir(folder)
    subFiles.remove(MAIN_CPP)
    print("files", subFiles)
    renameFileName = subFiles[0][0:-3] + "cpp"
    print("rename: ", renameFileName)

    os.rename(os.path.join(folder, MAIN_CPP), os.path.join(folder,renameFileName))
    shutil.copy(os.path.join(folder,renameFileName), ".")

