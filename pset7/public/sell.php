<?php

// Configuration
require("../includes/config.php");

// if user reached page via GET (as by clicking a link or via redirect)
if ($_SERVER["REQUEST_METHOD"] == "GET")
{
    // query database for user's stocks
    $rows = CS50::query("SELECT symbol FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
    $stocks = [];
    
    // Loop through stocks
    if (count($rows) >= 1)
    {
        foreach ($rows as $row) {
            $stocks[] = $row["symbol"];
        }
    }
    
    // render form
    render("sell_form.php", ["title" => "Sell Shares", "stocks" => $stocks]);
}

// else if user reached page via POST (as by submitting a form via POST)
else if ($_SERVER["REQUEST_METHOD"] == "POST")
{
    // Get shares of current stock
    $stock = lookup($_POST["symbol"]);
    $rows = CS50::query("SELECT shares FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
    
    if (count($rows) == 1) {
        // first (and only) row
        $row = $rows[0];
    
        $shares = $row["shares"];
        
        // Delete the row
        $delete = CS50::query("DELETE FROM portfolios WHERE user_id = ? AND symbol = ?", $_SESSION["id"], $_POST["symbol"]);
        $log = $insert = CS50::query(
            "INSERT IGNORE INTO history (user_id, symbol, shares, price, transaction) VALUES(?, ?, ?, ?, 'SOLD')", 
            $_SESSION["id"], 
            $_POST["symbol"],
            $shares,
            $stock["price"]
        );
        
        // Render error
        if ($delete == 0)
        {
            render("sell_form.php", 
            [ 
                "title" => "Sell Shares", 
                "error" => "Sale failed, please try again later."
            ]);
        }
        
        // Update Cash
        else 
        {
            // Update Cash
            $new_cash = $stock["price"] * $shares;
            $update = CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $new_cash, $_SESSION["id"]);
            
            // query database for user's balance
            $rows = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
            
            if (count($rows) == 1) {
                // first (and only) row
                $row = $rows[0];
                
                $cash = $row["cash"];
            }
            
            // render stock info
            render("balance.php", ["title" => "Sell Shares", "cash" => $cash]);
        }
    }
}