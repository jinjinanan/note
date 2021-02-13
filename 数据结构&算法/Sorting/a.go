package main

import "fmt"

//交换排序
// Bubble Sort
func bubbleSort(numbers []int) []int {
	var n = len(numbers)
	if n < 2 {
		return numbers
	}

	var temp int

	// var j int
	for i := 0; i < n-1; i++ {
		for j := 0; j < n-i-1; j++ {
			if numbers[j] > numbers[j+1] {
				temp = numbers[j]
				numbers[j] = numbers[j+1]
				numbers[j+1] = temp
			}
		}
	}

	return numbers
}

//插入排序
//Insertion Sort
func insertionSort(numbers []int) []int {
	var temp int

	for i := 0; i < len(numbers); i++ {
		temp = numbers[i]
		for j := i - 1; j >= 0; j-- {
			if temp < numbers[j] {
				numbers[j+1] = numbers[j]
				numbers[j] = temp
			} else {
				numbers[j+1] = temp
				break
			}

		}
		fmt.Println(temp, numbers)
	}
	return numbers
}

//Shell's Sort
//希尔排序数组里不可以有重复的数组

func ShellSort(numbers []int) []int {
	if len(numbers) < 2 {
		return numbers
	}
	key := len(numbers) / 2
	var temp int
	for key >= 1 {
		// j := 0
		for i := 0; i < key; i++ {
			for a := i; a < len(numbers); a = a + key {
				t := a
				for j := a; j < len(numbers); j = j + key {
					fmt.Println(i, j, t, numbers[t] < numbers[j], numbers)
					if numbers[t] > numbers[j] {
						temp = numbers[t]
						numbers[t] = numbers[j]
						numbers[j] = temp
					}
					t = j
				}
			}

		}
		key = key / 2
		fmt.Println("大循环", numbers)
	}

	return numbers
}

func ShellSort1(array []int) []int {
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
			fmt.Println(key, i, j, array)
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
		h = 3*h + 1
	}
	for h >= 1 {
		for i := h; i < n; i++ {
			for j := i; j >= h && arr[j] < arr[j-1]; j -= h {
				arr[j], arr[j-1] = arr[j-1], arr[j]
				fmt.Println(h, i, j, arr)
			}

		}
		h /= 3
	}
	return arr
}

//选择排序

//归并排序

const (
	sortOfInsert = iota
	sortOfShell
	sortOfBubble
)

func run(algorithmType int) {
	switch algorithmType {
	case sortOfInsert:
		fmt.Println("插入排序", insertionSort([]int{2, 1, 4, 7, 5, 1, 6, 8, 5}))
	case sortOfShell:
		fmt.Println("希尔排序", ShellSort([]int{2, 1, 4, 7, 5, 1, 6, 8, 5}))
	case sortOfBubble:
		fmt.Println("冒泡排序", bubbleSort([]int{2, 1, 4, 7, 5, 1, 6, 8, 5}))
	}

}

func main() {
	run(sortOfBubble)
}
