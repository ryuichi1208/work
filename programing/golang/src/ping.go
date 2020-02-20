package main

import (
  "fmt"
  "os/exec"
)

func main() {
  Command := fmt.Sprintf("ping -c 1 10.2.201.174 > /dev/null && echo true || echo false")
  output, err := exec.Command("/bin/sh", "-c", Command).Output()
  fmt.Print(string(output))
  fmt.Print(err)
}
