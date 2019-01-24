#!/usr/bin/python3
#-*- coding:utf-8 -*-
## ETNA PROJECT, 22-10-2018 by hauteb_m
## normes
## File description: 
##     check for ETNA normes. Love u Samantha <3
##

import sys

# In ETNA's pool you have to set a specific
# header with your code

def check_needed_spaces(line):
	#for i in range(0, len(lines)):
	if "){" in line:
		print("  [line %d] no space before curly bracket" % (j+1))
	elif "if(" in line:
		print("  [line %d] no space between if and parenthese" % (j+1))
	elif "for(" in line:
		print("  [line %d] no space between for and parenthese" % (j+1))
	elif "while(" in line:
		print("  [line %d] no space between while and parenthese" % (j+1))
	else :
		pass

def check_if_backline(line, line2):

	if "if" in line and ")\n" in line and "{" in line2 :
		print("  [line %d] no curly bracket after parenthese" % (j+1))
		print("  [line %d] curly bracket should be in the line above" % (j+2))

types = ["int ", "float ", "char ", "void "]

def check_curly_function(line):
	found = 0
	for type in types:
		if type in line and "{" in line and found == 0:
			found = 1
			print("  [line %d] found curly bracket after function" % (j+1))

def check_for_editor_header(line):
	if "ETNA PROJECT," in line:
		return True
	return False

def check_for_spaces(line):
	if line.endswith(" \n"):
		   print("  [line %d] space at EoL" % (j+1))

def check_for_tabs(line):
	if "\t" in line:
		print("  [line %d] found tab" % (j+1))

def check_for_stdio(line):
	if "stdio.h" in line:
		print("  [line %d] found stdio.h" % (j+1))

def check_for_printf(line):
	if "printf" in line:
		print("  [line %d] found printf" % (j+1))

if __name__ == '__main__':
	header = False
	check_start = 1

	if len(sys.argv) < 2:
		print("usage : normes.py [C file]")
		sys.exit(1)
	if sys.argv[1] == "--hard" :
		check_start = 2

	for i in range(check_start, len(sys.argv)):
		file_to_test = sys.argv[i]

		with open(file_to_test, "r") as f:
			print("file : %s" % sys.argv[i])
			lines = f.readlines()

			for j in range(0, len(lines)):
				if check_for_editor_header(lines[j]) == True:
					header = True

				check_curly_function(lines[j])
				check_needed_spaces(lines[j])
				check_for_spaces(lines[j])
				if check_start == 2:
					check_for_stdio(lines[j])
					check_for_printf(lines[j])
					check_for_tabs(lines[j])

				if j+1 < len(lines):
					check_if_backline(lines[j], lines[j+1])

			if header is False:
				print("  [ERROR] ETNA header not found")
