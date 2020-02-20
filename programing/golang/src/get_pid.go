package main

import (
    "fmt"
    "os"

    "github.com/mitchellh/go-ps"
)

func main() {
    currenProccessInfo()
}

func currenProccessInfo() {
    pid := os.Getpid()

    pidInfo, _ := ps.FindProcess(pid)

    fmt.Printf("%+v\n", pidInfo)

    fmt.Printf("> PID          : %d\n", pidInfo.Pid())
    fmt.Printf("> PPID         : %d\n", pidInfo.PPid())
    fmt.Printf("> Process name : %s\n", pidInfo.Executable())

    ppidInfo, _ := ps.FindProcess(pidInfo.PPid())
    fmt.Printf("> Parent process name : %s\n", ppidInfo.Executable())
}
