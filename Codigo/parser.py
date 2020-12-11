import sys

def delete_line(file, line):
    with open(file, "r") as infile:
        lines = infile.readlines()
    k = 0

    for k in range (0, len(lines)):
        if lines[k] == line:
            break

    with open(file, "w") as outfile:
        for pos, new_line in enumerate(lines):
            if pos != k:
                outfile.write(new_line)

def parse_decl(line, ous):
    decls = line.split()
    nvars = int(decls[2])
    for i in range(nvars):
        ous.write("(declare-const p%d Bool)\n" % (i + 1))    

def parse_clause(line, ous):
    literals = line.split()   
    assert (literals[-1] == '0')
    ous.write("(assert (or ")
    for p in literals:
        if p == '0':
           break
        if p[0] == '-':
           ous.write("(not p")
           ous.write(p[1:])
           ous.write(") ")
        else:
           ous.write("p")
           ous.write(p)
           ous.write(" ")
    ous.write("))\n")

def parse_file(file):
    ins = open(file)
    ous = open("%s.smt2" % file, 'w')
    ous.write("(set-logic QF_FD)\n")
    line = ins.readline()

    delete_line(file, line)

    parse_decl(line, ous)
    line = ins.readline()
    while line:
        if line[0][0] == "p":
            break

        delete_line(file, line)

        parse_clause(line, ous)
        line = ins.readline()
    ous.write("(check-sat)")
    ins.close()
    ous.close()

parse_file("2SAT.cnf")