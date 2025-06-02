#!/bin/sh

awk '
  # 1) Capture the current filename when we see "something.c: Error!" or "something.c: Notice!".
  /^[^:]+:[[:space:]]*(Error|Notice)!$/ {
    sep   = index($0, ":")
    fname = substr($0, 1, sep - 1)
    next
  }

  # 2) Match lines beginning with "Error:" or "Notice:", followed by the code, then "(line: XX, col: YY)".
  #    Capture into arr[2]=error_code, arr[3]=line, arr[4]=col.
  /^(Error|Notice):[[:space:]]*[^[:space:]]+[[:space:]]*\(line:[[:space:]]*[0-9]+,[[:space:]]*col:[[:space:]]*[0-9]+\)/ {
    if (match($0,
          /^(Error|Notice):[[:space:]]*([^[:space:]]+)[[:space:]]*\(line:[[:space:]]*([0-9]+),[[:space:]]*col:[[:space:]]*([0-9]+)\)/,
          arr))
    {
      code   = arr[2]
      lineNo = arr[3]
      colNo  = arr[4]
      if (fname != "") {
        printf "%s:%s:%s:%s\n", fname, lineNo, colNo, code
      }
    }
  }
' | sort -t: -k4,4
