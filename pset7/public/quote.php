<?php

    // configuration
    require("../includes/config.php"); 
    
    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        $stock = lookup($_POST["symbol"]);
        
        // check for valid symbol
         if (empty($stock["symbol"]))
        {
            apologize("Symbol not found.");
        }
        else
        {
            $price = number_format($stock["price"], 2, '.', ',');
            $msg = "A share of {$stock["name"]} ({$stock["symbol"]}), costs <strong>$$price</strong>. <br>";
            render("quote.php", ["title" => "Quote", "message" => "$msg"]);
        }
        
    }
    else
    {
        render("quote_form.php", ["title" => "Quote"]);
    }
    
?>
