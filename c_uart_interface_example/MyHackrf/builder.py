
import os

hackrfPath = "/libs/comphackrf/build"
repoUrl = "https://github.com/greatscottgadgets/hackrf.git"
repoPath = "ext/hackrf"
repoLibPath = "ext/hackrf/host"

root = os.getcwd()

def isLibBuilded()->bool:
    if not os.path.isdir(hackrfPath):
        return False
    elif not os.path.isfile(hackrfPath + "/libhackrf.so"):
        return False
    elif not os.path.isfile(hackrfPath + "/libhackrf.so.0"):
        return False
    elif not os.path.isfile(hackrfPath + "/libhackrf.so.0.9.0"):
        return False
    else:
        return True


if not isLibBuilded():
    res = 0
    if not os.path.isdir(repoPath):
        res = os.system(f"git clone {repoUrl} {repoPath}")
        if res != 0 : raise "clone hackrf repo fail"
    
    os.chdir(repoLibPath)
    if res != 0 : raise "cd fail"
    
    if not os.path.isdir("./build"):
        os.mkdir("build")

    os.chdir("build")
    os.system("cmake ..")
    if res != 0 : raise "cmake fail"

    os.system("make")
    if res != 0 : raise "make fail"

    os.chdir("libhackrf/src")
    
    path = root + hackrfPath
    if not os.path.isdir(path):
        os.mkdir(f"{path}")
    os.system(f"cp libhackrf.so {root}{hackrfPath}")
    os.system(f"cp libhackrf.so.0 {root}{hackrfPath}")
    os.system(f"cp libhackrf.so.0.9.0 {root}{hackrfPath}")

#os.chdir(root)
#if not os.path.isdir("build"):
#    os.mkdir("build")
#os.chdir("build")
#os.system("cmake ..")
#os.system("make")

