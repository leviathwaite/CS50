<?php
require("../templates/nav_links.php");
?>

<table class="table table-striped">

    <thead>
        <tr>
            <th>Symbol</th>
            <th>Name</th>
            <th>Shares</th>
            <th>Price</th>
            <th>TOTAL</th>
        </tr>
    </thead>

    <tbody>

    <?php
    $rows = get_user_portfolio();   
     
       
    foreach ($rows as $row)
    {
    // get name and current price
     $stock = lookup($row["symbol"]);
        
        // check for valid symbol
         if (empty($stock["symbol"]))
        {
            apologize("Database currupted.");
        }
        else
        {
            $price_current = $stock["price"];
            
        }
    
         //$value = $price_current * $row["shares"];
        $share_value = number_format(($price_current * $row["shares"]), 2, '.', ',');
    
        $price_current = number_format($stock["price"], 2, '.', ',');
    
        print("\n    <tr class='table-striped'>\n");
        print("\t <td>{$row["symbol"]}</td>\n");
        print("\t <td>{$stock["name"]}</td>\n");
        print("\t <td>{$row["shares"]}</td>\n");
        print("\t <td>\${$price_current}</td>\n");
        print("\t <td>\${$share_value}</td>\n");
        print("    </tr> \n");
        
        
    }
    
        // print out CASH
        print("\n    <tr id='cash'>\n");
        print("<td colspan='4'>Cash </td>");
        // get user's cash
        $cash = get_user_cash_dollars();
        print("<td >\${$cash}</td>");
        print("    </tr> \n");
    
    ?>

    </tbody>

</table>



