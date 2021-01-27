import threading
import time

# 创建线程的两种方法
# 一 将要执行的方法作为参数传给Thread的构造方法
# def action(arg):
#     time.sleep(2)
#     print('the arg is: %s in second way \r' % arg)

# for i in range(4):
#     t = threading.Thread(target=action,args=(i,))
#     t.start()

# print('the first way to create thread end')

# 二 从Thread继承，并重写run()
# class MyThread(threading.Thread):
#     def __init__(self,arg):
#         super().__init__()
#         self.arg = arg
    
#     def run(self):
#         time.sleep(2)
#         print('the arg is: %s in second way \r' % self.arg)

# for i in range(4):
#     t =MyThread(i)
#     t.start()

# print('the second way to create thread end')

# local
local = threading.local()
local.tname = 'main'
def func():
    local.tname = 'notmain'
    print(local.tname)
t = threading.Thread(target=func)
t.start()
t.join()
print(local.tname)