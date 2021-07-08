import matplotlib.pyplot as plt
import os 
import sys

def main():
    args = sys.argv
    if len(args) != 2:
        print('Usage: python plot.py NUM_FOLD')
        return
    num_fold = int(args[1])
    
    # draw precision-recall curve for the 10 folds
    for i in range(1, num_fold + 1):
        precision, recall, average = [], [], []

        with open("Fold{}/log.txt".format(str(i)),'r') as f:
            for line in f:
                summary = line.strip().split(" ")
                if (len(summary) == 1): continue
                precision.append(float(summary[1]))
                recall.append(float(summary[2]))
                average.append(float(summary[3]))
        
        print("Precision: " + str(precision) + "\nRecall: " + str(recall))

        plt.plot(recall, precision, color="gainsboro", label="Fold_{}".format(str(i)))
    
    # draw precision-recall curve for the average
    precision, recall = [], []
    
    with open("Cross_validation_log.txt",'r') as f:
        for line in f:
            summary = line.strip().split(" ")
            if (len(summary) == 1): continue
            precision.append(float(summary[1]))
            recall.append(float(summary[2]))
        print("Average run ____ Precision: " + str(precision) + "\nRecall: " + str(recall))

        plt.plot(recall, precision, color="red", label="Average Precision - Recall")
        
    plt.ylabel("Precision")
    plt.xlabel("Recall")
    plt.axis([0, 1, 0, 1])
    plt.legend(loc="lower left")
    plt.title("Precision-Recall at various thresholds")
    plt.savefig("precision_recall.png")

if __name__ == '__main__':
    main()

