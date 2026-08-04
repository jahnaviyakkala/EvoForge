from UserManagementService import UserManagementService, UserRepository

def main():
    user_repo = UserRepository()
    user_service = UserManagementService(user_repo)

    while True:
        print("\n1. Create User")
        print("2. Get User")
        print("3. Update User")
        print("4. Exit")
        choice = input("Enter your choice: ")

        if choice == '1':
            username = input("Enter username: ")
            email = input("Enter email: ")
            if user_service.create_user(username, email):
                print("User created successfully.")
            else:
                print("Failed to create user.")

        elif choice == '2':
            user_id = int(input("Enter user ID: "))
            user = user_service.get_user(user_id)
            if user:
                print(f"User ID: {user.user_id}, Username: {user.username}, Email: {user.email}")
            else:
                print("User not found.")

        elif choice == '3':
            user_id = int(input("Enter user ID: "))
            username = input("Enter new username: ")
            email = input("Enter new email: ")
            if user_service.update_user(user_id, username, email):
                print("User updated successfully.")
            else:
                print("Failed to update user.")

        elif choice == '4':
            break

        else:
            print("Invalid choice. Please try again.")

if __name__ == "__main__":
    main()
