<?php

// Configuration
require("../includes/config.php");

// if user reached page via GET (as by clicking a link or via redirect)
if ($_SERVER["REQUEST_METHOD"] == "GET")
{
    // render form
    render("buy_form.php", ["title" => "Buy Shares"]);
}

// else if user reached page via POST (as by submitting a form via POST)
else if ($_SERVER["REQUEST_METHOD"] == "POST")
{
    $stock = lookup($_POST["symbol"]);
    
    // check if stock is valid
    if ($stock === false)
    {
        render("buy_form.php", ["title" => "Buy Shares", "error" => "Not a valid stock symbol"]);
    }
    
    // check if number of shares is valid
    else if (!preg_match("/^\d+$/", $_POST["shares"])) 
    {
        render("buy_form.php", ["title" => "Buy Shares", "error" => "Number of shares must be a positive integer"]);
    }
    
    else
    {
        // query database for user's balance
        $rows = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    
        if (count($rows) == 1) {
            // first (and only) row
            $row = $rows[0];
        
            $cash = $row["cash"];
        }
        
        $purchase_price = $stock["price"] * $_POST["shares"];
        // Check if user has enough cash
        if ($purchase_price > $cash) 
        {
            render("buy_form.php", ["title" => "Buy Shares", "error" => "Not enough cash to purchase stocks."]);
        }
        
        // carry out transaction
        else 
        {
            $insert = CS50::query(
                "INSERT INTO portfolios (user_id, symbol, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)",
                $_SESSION["id"],
                $stock["symbol"],
                $_POST["shares"]
            );
            
            if ($insert === 0) 
            {
                render("buy_form.php", ["title" => "Buy Shares", "error" => "Purchase failed. Try again later."]);
            }
            
            // Update cash
            else {
                $update = CS50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $purchase_price, $_SESSION["id"]);
                
                // query database for user's balance
                $rows = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
                
                if (count($rows) == 1) {
                    // first (and only) row
                    $row = $rows[0];
                    
                    $cash = $row["cash"];
                }
                
                // render stock info
                render("balance.php", ["title" => "Buy Shares", "cash" => $cash]);
            }
        }
    }
}