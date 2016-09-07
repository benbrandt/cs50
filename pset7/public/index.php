<?php

    // configuration
    require("../includes/config.php"); 

    // query database for user's stocks
    $rows = CS50::query("SELECT symbol, shares FROM portfolios WHERE user_id = ?", $_SESSION["id"]);
    $stocks = [];

    // Loop through stocks
    if (count($rows) >= 1)
    {
        foreach ($rows as $row) {
            $stock = lookup($row["symbol"]);
            
            // Create associative array of values
            if ($stock != false) {
                $stocks[] = [
                    "name" => $stock["name"],
                    "symbol" => $row["symbol"],
                    "price" => $stock["price"],
                    "shares" => $row["shares"],
                ];
            }
        }
    }   
    
    // query database for user's balance
    $rows = CS50::query("SELECT cash FROM users WHERE id = ?", $_SESSION["id"]);
    
    if (count($rows) == 1) {
        // first (and only) row
        $row = $rows[0];
        
        $cash = $row["cash"];
    }

    // render portfolio
    render("portfolio.php", ["title" => "Portfolio", "stocks" => $stocks, "cash" => $cash]);

?>
