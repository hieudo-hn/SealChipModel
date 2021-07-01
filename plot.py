import matplotlib.pyplot as plt
import os 
import sys

def main():
    args = sys.argv
    if len(args) != 2:
        print('Usage: python plot.py PRECISION_RECALL.txt')
        return
    txtFile = args[1]

    precision, recall, average = [], [], []
    
    with open(txtFile ,'r') as f:
        for line in f:
            summary = line.strip().split(" ")
            if (len(summary) == 1): continue
            precision.append(float(summary[1]))
            recall.append(float(summary[2]))
            average.append(float(summary[3]))
    
    print("Precision: " + str(precision) + "\nRecall: " + str(recall))

    plt.plot(recall, precision)
    plt.ylabel("Precision")
    plt.xlabel("Recall")
    plt.axis([0, 1, 0, 1])
    plt.title("Precision-Recall at various thresholds")
    plt.savefig("precision_recall.png")

if __name__ == '__main__':
    main()

