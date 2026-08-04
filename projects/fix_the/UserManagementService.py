from typing import Optional

class User:
    def __init__(self, user_id: int, username: str, email: str):
        self.user_id = user_id
        self.username = username
        self.email = email

class UserRepository:
    def __init__(self):
        self.users = {}

    def save_user(self, user: User) -> bool:
        if user.user_id in self.users:
            return False
        self.users[user.user_id] = user
        return True

    def get_user_by_id(self, user_id: int) -> Optional[User]:
        return self.users.get(user_id)

    def update_user(self, user_id: int, username: str, email: str) -> bool:
        if user_id not in self.users:
            return False
        self.users[user_id].username = username
        self.users[user_id].email = email
        return True

class UserManagementService:
    def __init__(self, user_repository: UserRepository):
        self.user_repository = user_repository

    def create_user(self, username: str, email: str) -> bool:
        """
        Creates a new user with the given username and email.

        :param username: The username of the user to be created.
        :param email: The email address of the user to be created.
        :return: True if the user was successfully created, False otherwise.
        """
        # Implementation
        return self.user_repository.save_user(User(user_id=len(self.user_repository.users) + 1, username=username, email=email))

    def get_user(self, user_id: int) -> Optional[User]:
        """
        Retrieves a user by their ID.

        :param user_id: The ID of the user to retrieve.
        :return: The User object if found, None otherwise.
        """
        # Implementation
        return self.user_repository.get_user_by_id(user_id)

    def update_user(self, user_id: int, username: str, email: str) -> bool:
        """
        Updates an existing user's information.

        :param user_id: The ID of the user to update.
        :param username: The new username for the user.
        :param email: The new email address for the user.
        :return: True if the user was successfully updated, False otherwise.
        """
        # Implementation
        return self.user_repository.update_user(user_id, username, email)
