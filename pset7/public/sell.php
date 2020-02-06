<?php
    // configuration
    require("../includes/config.php");
    
     // if form was submitted
    if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // validate submission
        if (empty($_POST["sell_symbol"]))
        {
            apologize("You must select a stock to sell.");
        }
        
        // lookup stock
        $stock = lookup($_POST["sell_symbol"]);
        
        //SELECT * FROM `portfolio` WHERE id = 1 AND symbol = 'CAJ'
        
         // lookup portfolio
        $sale = get_user_portfolio();
        $shares = $sale[0]["shares"];
       
        
        // number of shares
        $_SESSION["sell_shares"] = $shares;
        
        // shares * current value
        $price = $stock["price"];
        $value = $shares * $price;
        
        // modify portfolio to "sell" stocks
        remove_stock($_SESSION["id"], $_POST["sell_symbol"]);
        
        // modify users Cash to reflect sale
        update_cash($value);
        
        // save in history, sell = 0
        insert_user_history(0, $_POST["sell_symbol"], $shares, $value);
        
         // redirect to portfolio
        redirect("/");
    }
    else
    {
     // lookup portfolio
    $rows = get_user_portfolio();
        
    // store in Session
    $_SESSION["portfolio"] = $rows;
    
    render("sell_form.php", ["title" => "Quote"]);
    }
?>
