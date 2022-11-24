#Bubble sort
from random import randint

def bubble(list_to_be_ordered):
    for i in range((len(list_to_be_ordered) - 1)):
        for j in range((len(list_to_be_ordered) - i - 1)):
            if(list_to_be_ordered[j] > list_to_be_ordered[j + 1]):
                aux = list_to_be_ordered[j]
                list_to_be_ordered[j] = list_to_be_ordered[j + 1]
                list_to_be_ordered[j + 1] = aux

def random_list_generator(new_list):
    for i in range(10):
        new_number = randint(i, i+6)
        new_list.append(new_number)


new_list = []
random_list_generator(new_list)
print(new_list)
bubble(new_list)
print(new_list)