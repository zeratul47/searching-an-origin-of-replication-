in_file = open('Salmonella_enterica.txt', 'r')
line = 1
in_str = ''
in_genome = ''
for in_data in in_file:
	in_str = in_data.strip(' \t\n\r')
	if(in_str[0] != '>'):
		in_genome += in_str


count_c = 0
count_g = 0
min1 = 0
minIndex = 0
skew_list = []
Skew = [0] * len(in_genome)
for i,v in enumerate(in_genome):
	if (v=="C"):
		count_c+=1
	elif(v=="G"):
		count_g+=1

	Skew[i] = (count_g-count_c)
	if(min1 > Skew[i]):
		minIndex = i
		min1 = Skew[i]
	if i-minIndex>100000 and minIndex not in skew_list:
		skew_list.append(minIndex)	

filename = 'ProbOriC'
for i in range(len(skew_list)):
	f_write = open(filename+str(skew_list[i])+'.txt', 'w')
	ProbOri = in_genome[skew_list[i]:skew_list[i]+1000]
	f_write.write(ProbOri)
	print filename+str(skew_list[i])+'.txt'
	f_write.close()
import matplotlib.pyplot as plt
plt.plot(Skew)
plt.show()