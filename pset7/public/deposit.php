<?php

// Configuration
require("../includes/config.php");

// if user reached page via GET (as by clicking a link or via redirect)
if ($_SERVER["REQUEST_METHOD"] == "GET")
{
    // render form
    render("deposit_form.php", ["title" => "Deposit Cash"]);
}

// else if user reached page via POST (as by submitting a form via POST)
else if ($_SERVER["REQUEST_METHOD"] == "POST")
{
    // check if deposit number is valid
    if (!preg_match("/^\d+$/", $_POST["amount"])) 
    {
        render("deposit_form.php", ["title" => "Deposit Cash", "error" => "Number must be a positive integer"]);
    }
    
    else
    {
        // update user's balance
        $update = CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $_POST["amount"], $_SESSION["id"]);
                
        // query database for user's balance
        $rows = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
        
        if (count($rows) == 1) {
            // first (and only) row
            $row = $rows[0];
            
            $cash = $row["cash"];
        }
        
        // render stock info
        render("balance.php", ["title" => "Balance", "cash" => $cash]);
    }
}