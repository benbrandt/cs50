<?php

// Configuration
require("../includes/config.php");

// if user reached page via GET (as by clicking a link or via redirect)
if ($_SERVER["REQUEST_METHOD"] == "GET")
{
    // render form
    render("register_form.php", ["title" => "Register"]);
}

// else if user reached page via POST (as by submitting a form via POST)
else if ($_SERVER["REQUEST_METHOD"] == "POST")
{
    // Validate form
    if ($_POST["username"] == "" || 
        $_POST["password"] == "" || 
        $_POST["password"] !== $_POST["confirmation"])
    {
        render("register_form.php", 
            [ 
                "title" => "Register", 
                "error" => "Please fill out all fields and ensure your password fields match"
            ]);
    }
    
    // Register User
    else
    {
        $insert = CS50::query(
            "INSERT IGNORE INTO users (username, hash, cash) VALUES(?, ?, 10000.0000)", 
            $_POST["username"], 
            password_hash($_POST["password"], PASSWORD_DEFAULT)
        );
        
        // Check if insert succeeded
        if ($insert == 0)
        {
            render("register_form.php", 
            [ 
                "title" => "Register", 
                "error" => "Sign up failed, please try again later."
            ]);
        }
        
        // If successful, Login User
        else
        {
            $rows = CS50::query("SELECT LAST_INSERT_ID() AS id");
            $id = $rows[0]["id"];
            
            // remember that user's now logged in by storing user's ID in session
            $_SESSION["id"] = $id;

            // redirect to portfolio
            redirect("/");
        }
    }
}