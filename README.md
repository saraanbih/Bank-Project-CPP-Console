# **Bank Project (OOP)**  

## **Project Overview**  
This project is designed to simulate a basic banking system using Object-Oriented Programming (OOP) principles. It requires users to log in with a valid username and password, and after successful login, they will have access to a **Main Menu** with various banking operations. If the user fails to enter correct credentials within three attempts, the program locks, ensuring security.  

The project is structured with multiple options and submenus for managing clients, transactions, users, and more. The application also includes a string validation library and a date/time library for enhanced functionality.

---

## **Features**  

### **Login System**  
- The system requires the user to input their **username** and **password**.
- If the user enters the wrong credentials three times, the program locks for security purposes.
- After successful login, the **login time** and **user details** are registered.
- The **Main Menu** is then displayed with various options.

### **Main Menu**  
The Main Menu includes the following **10 options**:

1. **Client Screen**  
   - Displays information about clients in the system.
  
2. **Add New Client**  
   - Allows users to add new clients by entering their details (e.g., name, account number, balance).

3. **Delete Client**  
   - Allows users to delete a client from the system.

4. **Update Client Info**  
   - Users can update information of an existing client (e.g., change balance, contact info).

5. **Find Client**  
   - Search for a client by their ID or name.

6. **Transactions**  
   - This screen includes the following **subscreens**:  
     - **Deposit**: Add funds to a client's account.  
     - **Withdraw**: Remove funds from a client's account.  
     - **Total Balances**: View the total balance of a client.  
     - **Transfer**: Transfer funds between clients.  
     - **Transfer Log**: View the history of transfers.

7. **Manage Users**  
   - This menu includes the following **subscreens**:  
     - **List Users**: Display all registered users.  
     - **Add New User**: Add a new user to the system.  
     - **Delete User**: Remove a user from the system.  
     - **Update User Info**: Edit the details of a user.  
     - **Find User**: Search for a user by their ID or username.

8. **Login Register**  
   - Users can register new usernames and passwords or edit existing ones.

9. **Currency Exchange**  
   - This screen includes the following **subscreens**:  
     - **List Currencies**: View all available currencies.  
     - **Find Currency**: Search for a specific currency.  
     - **Update Rate**: Change the exchange rate for a specific currency.  
     - **Currency Calculator**: Calculate currency conversion between different currencies.

10. **Logout**  
    - Returns the user to the login screen.

---

### **Submenu Functionality**  
- In any of the submenus mentioned above, users will also have the option to **return to the main menu** at any point.

---

## **Libraries Used**  

- **String Library**:  
  A custom string library is included, which offers various string manipulation functions for tasks like validation and formatting.
  
- **Validate Library**:  
  A library for input validation is used to ensure the integrity of data entered by users, such as verifying if a number is positive or if input meets certain criteria.

---

## **How to Use**  

1. **Start the Application**:  
   Run the executable file to launch the bank system.

2. **Login**:  
   - You will be prompted to enter your **username** and **password**.  
   - If your credentials are incorrect three times, the program will lock for security.  
   - If you enter the correct details, the system will log the **time** of the login and display the **Main Menu**.

3. **Main Menu**:  
   - From the Main Menu, choose from the available options (e.g., view client info, make transactions, manage users, etc.).
   - Each option may have submenus that further define actions for managing clients, transactions, users, etc.

4. **Logout**:  
   - Once you're done, choose the **Logout** option to return to the login screen.

---

## **Conclusion**  
Thank you for checking out the **Bank Project (OOP)**! I hope this project serves as a useful tool and provides insight into how Object-Oriented Programming can be applied in real-world systems. Feel free to explore, contribute, and suggest improvements to make it even better!
