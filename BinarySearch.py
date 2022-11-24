from random import randrange

def list_generator(new_list, number_of_elements, interval):
    for i in range(0, number_of_elements*interval, 4):      #Generates a random list
        new_number = randrange(i, i+4)
        new_list.append(new_number)

def binary_search(obj_list, number_searched, start, finish):
    center = int((start+finish)/2)
    if(start > finish):
        return -1
    elif(obj_list[center] == number_searched):              #Binary search
        return center
    elif(obj_list[center] > number_searched):
        return(binary_search(obj_list, number_searched, start, center-1))
    elif(obj_list[center] < number_searched):
        return(binary_search(obj_list, number_searched, center+1, finish))

new_list = []
number_of_elements = int(input("Please enter the desired number of elements in the list: "))
list_generator(new_list, number_of_elements, 4)
print(new_list)
number_to_be_searched = int(input("Number that you want to check on the list: "))

if(binary_search(new_list, number_to_be_searched, 0, len(new_list)) == -1):
    print("The number is not in the list")
else:
    print("The number is in position number:", binary_search(new_list, number_to_be_searched, 0, len(new_list)))