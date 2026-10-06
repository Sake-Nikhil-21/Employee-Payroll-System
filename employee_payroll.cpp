#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

int main() {

    string html = R"HTML(
<!DOCTYPE html>
<html>
<head>
    <title>Employee Payroll System</title>

    <style>
        body {
            font-family: Arial, sans-serif;
            margin: 0;
            background: #f4f6f8;
        }

        header {
            background: #1f4e79;
            color: white;
            padding: 20px;
            text-align: center;
        }

        .container {
            width: 90%;
            margin: 25px auto;
        }

        .card {
            background: white;
            padding: 20px;
            margin-bottom: 20px;
            border-radius: 10px;
            box-shadow: 0 2px 8px #ccc;
        }

        input, button {
            padding: 10px;
            margin: 5px;
        }

        button {
            background: #1f4e79;
            color: white;
            border: none;
            border-radius: 5px;
            cursor: pointer;
        }

        table {
            width: 100%;
            border-collapse: collapse;
            margin-top: 15px;
        }

        th, td {
            border: 1px solid #ddd;
            padding: 10px;
            text-align: center;
        }

        th {
            background: #1f4e79;
            color: white;
        }

        .login {
            max-width: 400px;
            margin: 80px auto;
            text-align: center;
        }

        #dashboard {
            display: none;
        }
    </style>
</head>

<body>

<header>
    <h1>Employee Payroll System</h1>
    <p>Employee Management and Payroll Dashboard</p>
</header>

<div class="container">

    <div class="card login" id="loginBox">
        <h2>Login</h2>

        <input type="text" id="username" placeholder="Username"><br>

        <input type="password" id="password"
               placeholder="Password"><br>

        <button onclick="login()">Login</button>

        <p id="loginMessage"></p>
    </div>


    <div id="dashboard">

        <div class="card">
            <h2>Dashboard</h2>
            <p>Welcome to the Employee Payroll Management System.</p>
        </div>


        <div class="card">
            <h2>Add Employee</h2>

            <input type="text" id="empName"
                   placeholder="Employee Name">

            <input type="text" id="empRole"
                   placeholder="Role">

            <input type="number" id="basic"
                   placeholder="Basic Salary">

            <button onclick="addEmployee()">
                Add Employee
            </button>
        </div>


        <div class="card">
            <h2>Employee Records</h2>

            <table>
                <thead>
                    <tr>
                        <th>Name</th>
                        <th>Role</th>
                        <th>Basic Salary</th>
                        <th>Net Salary</th>
                    </tr>
                </thead>

                <tbody id="employeeTable">
                </tbody>
            </table>
        </div>


        <div class="card">
            <h2>Payroll Calculation</h2>

            <p>HRA = 20% of Basic Salary</p>
            <p>DA = 10% of Basic Salary</p>
            <p>Bonus = ₹5,000</p>
            <p>EPF = 12% of Basic Salary</p>
            <p>Professional Tax = ₹200</p>

            <button onclick="showPayroll()">
                Calculate Payroll
            </button>

            <div id="payrollResult"></div>
        </div>


        <div class="card">
            <h2>Attendance</h2>

            <input type="number"
                   id="workingDays"
                   placeholder="Working Days">

            <input type="number"
                   id="presentDays"
                   placeholder="Present Days">

            <button onclick="calculateAttendance()">
                Calculate Deduction
            </button>

            <p id="attendanceResult"></p>
        </div>


        <div class="card">
            <h2>Payslip</h2>

            <button onclick="printPayslip()">
                Print Payslip
            </button>
        </div>

    </div>

</div>


<script>

let employees = [];

function login() {

    let username =
        document.getElementById("username").value;

    let password =
        document.getElementById("password").value;

    if (username === "admin" &&
        password === "admin123") {

        document.getElementById("loginBox")
                .style.display = "none";

        document.getElementById("dashboard")
                .style.display = "block";

    } else {

        document.getElementById("loginMessage")
                .innerHTML =
                "Invalid username or password";
    }
}


function addEmployee() {

    let name =
        document.getElementById("empName").value;

    let role =
        document.getElementById("empRole").value;

    let basic =
        Number(document.getElementById("basic").value);

    if (name === "" || role === "" || basic <= 0) {
        alert("Please enter valid employee details.");
        return;
    }

    let hra = basic * 0.20;
    let da = basic * 0.10;
    let bonus = 5000;

    let gross = basic + hra + da + bonus;

    let epf = basic * 0.12;
    let tax = 200;

    let netSalary = gross - epf - tax;

    employees.push({
        name: name,
        role: role,
        basic: basic,
        net: netSalary
    });

    displayEmployees();

    document.getElementById("empName").value = "";
    document.getElementById("empRole").value = "";
    document.getElementById("basic").value = "";
}


function displayEmployees() {

    let table =
        document.getElementById("employeeTable");

    table.innerHTML = "";

    employees.forEach(function(emp) {

        let row = table.insertRow();

        row.insertCell(0).innerHTML = emp.name;
        row.insertCell(1).innerHTML = emp.role;
        row.insertCell(2).innerHTML =
            "₹" + emp.basic.toFixed(2);

        row.insertCell(3).innerHTML =
            "₹" + emp.net.toFixed(2);
    });
}


function showPayroll() {

    if (employees.length === 0) {
        alert("Please add an employee first.");
        return;
    }

    let emp = employees[employees.length - 1];

    let basic = emp.basic;

    let hra = basic * 0.20;
    let da = basic * 0.10;
    let bonus = 5000;

    let gross = basic + hra + da + bonus;

    let epf = basic * 0.12;
    let tax = 200;

    let net = gross - epf - tax;

    document.getElementById("payrollResult")
        .innerHTML =
        "<h3>Payroll Details</h3>" +
        "Basic Salary: ₹" + basic.toFixed(2) + "<br>" +
        "HRA: ₹" + hra.toFixed(2) + "<br>" +
        "DA: ₹" + da.toFixed(2) + "<br>" +
        "Bonus: ₹" + bonus.toFixed(2) + "<br>" +
        "Gross Salary: ₹" + gross.toFixed(2) + "<br>" +
        "EPF: ₹" + epf.toFixed(2) + "<br>" +
        "Professional Tax: ₹" + tax.toFixed(2) + "<br>" +
        "<strong>Net Salary: ₹" + net.toFixed(2) +
        "</strong>";
}


function calculateAttendance() {

    let working =
        Number(document.getElementById("workingDays").value);

    let present =
        Number(document.getElementById("presentDays").value);

    if (working <= 0 || present < 0 || present > working) {
        alert("Enter valid attendance details.");
        return;
    }

    let absent = working - present;

    document.getElementById("attendanceResult")
        .innerHTML =
        "Absent Days: " + absent;
}


function printPayslip() {

    window.print();
}

</script>

</body>
</html>
)HTML";


    // Create the HTML file
    ofstream file("employee_payroll.html");

    if (!file) {
        cout << "Error creating HTML file." << endl;
        return 1;
    }

    file << html;
    file.close();


    cout << "Employee Payroll System created successfully!"
         << endl;

    cout << "Opening employee_payroll.html..." << endl;


    // Open HTML file in default browser
    #ifdef _WIN32
        system("start employee_payroll.html");
    #elif __APPLE__
        system("open employee_payroll.html");
    #else
        system("xdg-open employee_payroll.html");
    #endif


    return 0;
}
