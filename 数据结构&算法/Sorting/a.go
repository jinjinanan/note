package main

import "fmt"

func insertSort(numbers []int) []int{
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

func main(){
	fmt.Println("插入排序",insertSort([]int{2,1,4,7,5,1,6,8,5}))
}

