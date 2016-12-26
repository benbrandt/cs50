<?php

// Configuration
require("../includes/config.php");

// if user reached page via GET (as by clicking a link or via redirect)
if ($_SERVER["REQUEST_METHOD"] == "GET")
{
    // render form
    render("quote_form.php", ["title" => "Get Quote"]);
}

// else if user reached page via POST (as by submitting a form via POST)
else if ($_SERVER["REQUEST_METHOD"] == "POST")
{
    $stock = lookup($_POST["symbol"]);
    
    if ($stock !== false)
    {
        // render stock info
        render("quote.php", ["title" => "Get Quote", "stock" => $stock]);
    }
    
    // Render error
    else
    {
        render("quote.php", ["title" => "Get Quote", "error" => "No stock info for {$_POST["symbol"]}. Try again."]);
    }
}