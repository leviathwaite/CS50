<?php

    // configuration
    require("../includes/config.php"); 

    // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["symbol"]))
        {
            apologize("You must specify a stock to buy.");
        }
        if (empty($_POST["shares"]))
        {
            apologize("You must specify a number of shares.");
        }
        // check that shares are positive full numbers
        if (!preg_match('{^[0-9]{1,6}$}',$_POST["shares"]) && $_POST["shares"] <= 0)
        {
            apologize("Invalid number of shares.");
        }
        // if empty not valid
        if (empty($_POST["symbol"]))
        {
            apologize("Symbol not found.");
        }
        else
        {
            // check for valid symbol
            $stock = lookup($_POST["symbol"]);
        
            // get price
            $price = $stock["price"];
         
            // times price by number of shares
            $shares = $_POST["shares"];
            $total = $price * $shares;
            
            // check that user has enough cash
            $cash = get_user_cash();
            if($total > $cash)
            {
                 apologize("You can't afford that.");
            }
            // add stock to database
            insert_stock($_POST["symbol"], $_POST["shares"]);
            
            // subtract cash from user
            update_cash(-$total);
            
            // save in history, buy = 1
            // $transaction, $symbol, $shares, $price
            insert_user_history(1, $_POST["symbol"], $_POST["shares"], $total);
          
        }
        
        // redirect to portfolio
        redirect("/");
    }
    else
    {
        // else render form
        render("buy_form.php", ["title" => "Log In"]);
    }

?>
