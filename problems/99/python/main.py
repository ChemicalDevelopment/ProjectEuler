import math
# keep track of max log, linenum, and result string of the operation
max_log = 1.0
linenm = 0
resstr = ""

# read in the csv, and split in on newlines
data = open("../base_exp.txt", "r").read().split("\n")

# loop through
for i in data:
	# parse int list
	sp = map(int, i.split(","))
	# calculate log, this is a strictly increasing function, so this will sort ordinally
	res_log = sp[1] * math.log(sp[0])
	# if we beat the previous max, update the vars
	if res_log > max_log: 
		max_log = res_log
		linenm = data.index(i) + 1
		resstr = "%d**%d" % (sp[0], sp[1])

# print info
print "Maximum value is %s at line number %d, having log10 of %f" % (resstr, linenm, max_log)

