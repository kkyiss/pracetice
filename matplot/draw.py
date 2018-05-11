import matplotlib.pyplot as plt

# Read file in
def readin(filename):
	arr = []
	while True:
		# format (0,0)
		line = filename.readline()
		if not line:
			break

		p =  line.split('\n')
		if p[0]:
			arr.append(int(p[0].split(' ')[1]))

	return arr

# fopen
fopen = open('filename.txt','r')
farr = readin(fopen)

# fclose
fopen.close()


# x-axis
x=[]
for i in range(len(farr)):
	x.append(int(i))


# title
plt.title('title name')
plt.ylabel('y axle')
plt.xlabel('x axle')

# result lines
plt.plot(x,farr)


# annotation
plt.legend(['a'], loc='upper right')

plt.show()
