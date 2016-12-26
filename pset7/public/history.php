<?php

    // configuration
    require("../includes/config.php"); 

    // query database for user's stocks
    $rows = CS50::query("SELECT symbol, shares, price, transaction, time FROM history WHERE user_id = ?", $_SESSION["id"]);
    $transactions = [];

    // Loop through stocks
    if (count($rows) >= 1)
    {
        foreach ($rows as $row) {
            $transactions[] = $row;
        }
    }   
    
    // render portfolio
    render("history.php", ["title" => "History", "transactions" => $transactions]);

?>
