# 2024-11-23
# 张逸飞
# 231051010616
# 计算机科学与技术6班
import tkinter as tk
from tkinter import messagebox
import random

class GuessNumberGame(tk.Tk):
    def __init__(self):
        super().__init__()

        self.title("猜数游戏")
        self.geometry("300x150")

        self.secret_number = random.randint(0, 1024)
        self.attempts = 0

        self.label = tk.Label(self, text="请输入0到1024之间的数字：")
        self.label.pack(pady=10)

        self.entry = tk.Entry(self)
        self.entry.pack(pady=5)

        self.submit_button = tk.Button(self, text="提交", command=self.check_guess)
        self.submit_button.pack(pady=5)

    def check_guess(self):
        guess = int(self.entry.get())
        self.attempts += 1

        if guess < self.secret_number:
            messagebox.showinfo("提示", "太低了！请再试一次。")
        elif guess > self.secret_number:
            messagebox.showinfo("提示", "太高了！请再试一次。")
        else:
            messagebox.showinfo("恭喜", f"恭喜你，猜对了！你一共猜了{self.attempts}次。")
            self.secret_number = random.randint(0, 1024)  # 生成新的随机数，重新开始游戏
            self.attempts = 0

if __name__ == "__main__":
    game = GuessNumberGame()
    game.mainloop()
