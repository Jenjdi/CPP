import tkinter as tk
from tkinter import messagebox


# 模拟数据库，存储数据
rooms = []
guests = []
bookings = []
admin_username = "admin"
admin_password = "123456"


# 管理员登录函数
def admin_login():
    username = username_entry.get()
    password = password_entry.get()
    if username == admin_username and password == admin_password:
        login_window.destroy()
        show_main_menu()
    else:
        messagebox.showerror("登录失败", "用户名或密码错误")


# 显示主菜单
def show_main_menu():
    main_menu_window = tk.Tk()
    main_menu_window.title("宾馆客房信息管理系统 - 主菜单")

    # 客房信息管理按钮
    room_manage_button = tk.Button(main_menu_window, text="客房信息管理", command=room_management)
    room_manage_button.pack(pady=10)

    # 客户信息管理按钮
    guest_manage_button = tk.Button(main_menu_window, text="客户信息管理", command=guest_management)
    guest_manage_button.pack(pady=10)

    # 订房退房管理按钮
    booking_manage_button = tk.Button(main_menu_window, text="订房退房管理", command=booking_management)
    booking_manage_button.pack(pady=10)

    main_menu_window.mainloop()


# 客房信息管理
def room_management():
    room_window = tk.Tk()
    room_window.title("客房信息管理")

    # 录入客房信息
    def add_room():
        room_number = room_number_entry.get()
        room_type = room_type_entry.get()
        capacity = capacity_entry.get()
        if room_number and room_type and capacity:
            rooms.append({"room_number": room_number, "room_type": room_type, "capacity": capacity})
            messagebox.showinfo("成功", "客房信息添加成功")
            clear_room_entries()
        else:
            messagebox.showerror("错误", "请填写完整客房信息")

    # 修改客房信息
    def update_room():
        selected_index = room_listbox.curselection()
        if selected_index:
            index = selected_index[0]
            room_number = room_number_entry.get()
            room_type = room_type_entry.get()
            capacity = capacity_entry.get()
            if room_number and room_type and capacity:
                rooms[index]["room_number"] = room_number
                rooms[index]["room_type"] = room_type
                rooms[index]["capacity"] = capacity
                messagebox.showinfo("成功", "客房信息修改成功")
                clear_room_entries()
                load_rooms()
            else:
                messagebox.showerror("错误", "请填写完整客房信息")
        else:
            messagebox.showerror("错误", "请选择要修改的客房")

    # 删除客房信息
    def delete_room():
        selected_index = room_listbox.curselection()
        if selected_index:
            index = selected_index[0]
            del rooms[index]
            messagebox.showinfo("成功", "客房信息删除成功")
            load_rooms()
        else:
            messagebox.showerror("错误", "请选择要删除的客房")

    # 查询客房信息
    def search_room():
        search_key = search_entry.get()
        result_rooms = []
        for room in rooms:
            if search_key in room["room_number"] or search_key in room["room_type"]:
                result_rooms.append(room)
        load_rooms(result_rooms)

    # 加载客房信息到列表框
    def load_rooms(room_list=rooms):
        room_listbox.delete(0, tk.END)
        for room in room_list:
            room_listbox.insert(tk.END, f"客房号: {room['room_number']}, 类型: {room['room_type']}, 容量: {room['capacity']}")

    # 清空输入框
    def clear_room_entries():
        room_number_entry.delete(0, tk.END)
        room_type_entry.delete(0, tk.END)
        capacity_entry.delete(0, tk.END)

    # 客房号标签和输入框
    room_number_label = tk.Label(room_window, text="客房号:")
    room_number_label.pack()
    room_number_entry = tk.Entry(room_window)
    room_number_entry.pack()

    # 客房类型标签和输入框
    room_type_label = tk.Label(room_window, text="客房类型:")
    room_type_label.pack()
    room_type_entry = tk.Entry(room_window)
    room_type_entry.pack()

    # 容量标签和输入框
    capacity_label = tk.Label(room_window, text="容量:")
    capacity_label.pack()
    capacity_entry = tk.Entry(room_window)
    capacity_entry.pack()

    # 添加客房按钮
    add_button = tk.Button(room_window, text="添加客房", command=add_room)
    add_button.pack(pady=5)

    # 修改客房按钮
    update_button = tk.Button(room_window, text="修改客房", command=update_room)
    update_button.pack(pady=5)

    # 删除客房按钮
    delete_button = tk.Button(room_window, text="删除客房", command=delete_room)
    delete_button.pack(pady=5)

    # 搜索标签和输入框
    search_label = tk.Label(room_window, text="搜索客房:")
    search_label.pack()
    search_entry = tk.Entry(room_window)
    search_entry.pack()

    # 搜索按钮
    search_button = tk.Button(room_window, text="搜索", command=search_room)
    search_button.pack(pady=5)

    # 客房信息列表框
    room_listbox = tk.Listbox(room_window)
    room_listbox.pack()
    load_rooms()

    room_window.mainloop()


# 客户信息管理
def guest_management():
    guest_window = tk.Tk()
    guest_window.title("客户信息管理")

    # 录入客户信息
    def add_guest():
        guest_name = guest_name_entry.get()
        contact_info = contact_info_entry.get()
        if guest_name and contact_info:
            guests.append({"guest_name": guest_name, "contact_info": contact_info})
            messagebox.showinfo("成功", "客户信息添加成功")
            clear_guest_entries()
        else:
            messagebox.showerror("错误", "请填写完整客户信息")

    # 修改客户信息
    def update_guest():
        selected_index = guest_listbox.curselection()
        if selected_index:
            index = selected_index[0]
            guest_name = guest_name_entry.get()
            contact_info = contact_info_entry.get()
            if guest_name and contact_info:
                guests[index]["guest_name"] = guest_name
                guests[index]["contact_info"] = contact_info
                messagebox.showinfo("成功", "客户信息修改成功")
                clear_guest_entries()
                load_guests()
            else:
                messagebox.showerror("错误", "请填写完整客户信息")
        else:
            messagebox.showerror("错误", "请选择要修改的客户")

    # 查询客户信息
    def search_guest():
        search_key = search_entry.get()
        result_guests = []
        for guest in guests:
            if search_key in guest["guest_name"]:
                result_guests.append(guest)
        load_guests(result_guests)

    # 加载客户信息到列表框
    def load_guests(guest_list=guests):
        guest_listbox.delete(0, tk.END)
        for guest in guest_list:
            guest_listbox.insert(tk.END, f"客户姓名: {guest['guest_name']}, 联系方式: {guest['contact_info']}")

    # 清空输入框
    def clear_guest_entries():
        guest_name_entry.delete(0, tk.END)
        contact_info_entry.delete(0, tk.END)

    # 客户姓名标签和输入框
    guest_name_label = tk.Label(guest_window, text="客户姓名:")
    guest_name_label.pack()
    guest_name_entry = tk.Entry(guest_window)
    guest_name_entry.pack()

    # 联系方式标签和输入框
    contact_info_label = tk.Label(guest_window, text="联系方式:")
    contact_info_label.pack()
    contact_info_entry = tk.Entry(guest_window)
    contact_info_entry.pack()

    # 添加客户按钮
    add_button = tk.Button(guest_window, text="添加客户", command=add_guest)
    add_button.pack(pady=5)

    # 修改客户按钮
    update_button = tk.Button(guest_window, text="修改客户", command=update_guest)
    update_button.pack(pady=5)

    # 搜索标签和输入框
    search_label = tk.Label(guest_window, text="搜索客户:")
    search_label.pack()
    search_entry = tk.Entry(guest_window)
    search_entry.pack()

    # 搜索按钮
    search_button = tk.Button(guest_window, text="搜索", command=search_guest)
    search_button.pack(pady=5)

    # 客户信息列表框
    guest_listbox = tk.Listbox(guest_window)
    guest_listbox.pack()
    load_guests()

    guest_window.mainloop()


# 订房退房信息管理
def booking_management():
    booking_window = tk.Tk()
    booking_window.title("订房退房信息管理")

    # 订房函数
    def book_room():
        room_number = room_number_entry.get()
        guest_name = guest_name_entry.get()
        for room in rooms:
            if room["room_number"] == room_number:
                bookings.append({"room_number": room_number, "guest_name": guest_name})
                messagebox.showinfo("成功", "订房成功")
                clear_booking_entries()
                return
        messagebox.showerror("错误", "客房不存在")

    # 退房函数
    def check_out():
        room_number = room_number_entry.get()
        for booking in bookings:
            if booking["room_number"] == room_number:
                bookings.remove(booking)
                messagebox.showinfo("成功", "退房成功")
                clear_booking_entries()
                return
        messagebox.showerror("错误", "未找到该客房的订房记录")

    # 加载订房信息到列表框
    def load_bookings():
        booking_listbox.delete(0, tk.END)
        for booking in bookings:
            booking_listbox.insert(tk.END, f"客房号: {booking['room_number']}, 客户姓名: {booking['guest_name']}")

    # 清空输入框
    def clear_booking_entries():
        room_number_entry.delete(0, tk.END)
        guest_name_entry.delete(0, tk.END)

    # 客房号标签和输入框
    room_number_label = tk.Label(booking_window, text="客房号:")
    room_number_label.pack()
    room_number_entry = tk.Entry(booking_window)
    room_number_entry.pack()

    # 客户姓名标签和输入框
    guest_name_label = tk.Label(booking_window, text="客户姓名:")
    guest_name_label.pack()
    guest_name_entry = tk.Entry(booking_window)
    guest_name_entry.pack()

    # 订房按钮
    book_button = tk.Button(booking_window, text="订房", command=book_room)
    book_button.pack(pady=5)

    # 退房按钮
    check_out_button = tk.Button(booking_window, text="退房", command=check_out)
    check_out_button.pack(pady=5)

    # 订房信息列表框
    booking_listbox = tk.Listbox(booking_window)
    booking_listbox.pack()
    load_bookings()

    booking_window.mainloop()


# 创建登录窗口
login_window = tk.Tk()
login_window.title("管理员登录")

# 用户名标签和输入框
username_label = tk.Label(login_window, text="用户名:")
username_label.pack()
username_entry = tk.Entry(login_window)
username_entry.pack()

# 密码标签和输入框
password_label = tk.Label(login_window, text="密码:")
password_label.pack()
password_entry = tk.Entry(login_window, show="*")
password_entry.pack()

# 登录按钮
login_button = tk.Button(login_window, text="登录", command=admin_login)
login_button.pack(pady=10)

login_window.mainloop()