package main

import "fmt"



//Insertion Sort
func insertionSort(numbers []int) []int{
	var temp int

	for i:= 0; i<len(numbers);i++{
		temp = numbers[i]
		for j:=i-1;j >= 0;j--{
			if temp < numbers[j]{
				numbers[j+1] = numbers[j]
				numbers[j] = temp
			} else {
				numbers[j+1] = temp
				break
			}
			
		}
		fmt.Println(temp,numbers)
	}
	return numbers
}

//Shell's Sort
//希尔排序数组里不可以有重复的数组

func ShellSort(numbers []int) []int{
	if len(numbers) < 2{
		return numbers
	}
	key := len(numbers)/2
	var temp int
	for key >= 1 {
		j := 0
		for ii :=0; ii < key; ii++ {
			j = ii
			for i := ii; i<len(numbers);i = i+key{
				fmt.Println(i,j,numbers[i] < numbers[j],numbers)
				if(numbers[i] < numbers[j]){
					temp = numbers[i]
					numbers[i] = numbers[j]
					numbers[j] = temp
					// fmt.Println("交换",numbers[j],numbers[i],temp)
				} 
				j = i
			}
		}
		key = key/2
		fmt.Println("大循环",numbers)
	}
	
	return numbers
}

func ShellSort1(array []int) []int{
	n := len(array)
	if n < 2 {
		return array
	}
	key := n / 2
	for key > 0 {
		for i := key; i < n; i++ {
			j := i
			for j >= key && array[j] < array[j-key] {
				array[j], array[j-key] = array[j-key], array[j]
				j = j - key
			}
			fmt.Println(key,i,j,array)
		}
		key = key / 2
		
	}
	return array
}

func ShellSort2(arr []int) []int {
    n := len(arr)
    h := 1
    //寻找合适的间隔h
    for h < n/3 {
        h = 3*h +1
    }
    for h >= 1 {
        for i := h; i < n; i++ {
            for j := i; j >= h && arr[j] < arr[j-1]; j -= h {
				arr[j], arr[j-1] = arr[j-1], arr[j]
				fmt.Println(h,i,j,arr)
			}
			
		}
		h /= 3
	}
	return arr
}

const(
	sortOfInsert = iota
	sortOfShell
)

func run(algorithmType int){
	switch algorithmType {
	case sortOfInsert:
		fmt.Println("插入排序",insertionSort([]int{2,1,4,7,5,1,6,8,5}))
	case sortOfShell:
		fmt.Println("希尔排序",ShellSort2([]int{2,1,4,7,5,1,6,8,5}))
	}
}

func main(){
	run(sortOfShell)
}

