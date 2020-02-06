<?php
require("../templates/nav_links.php");
?>
<form action="sell.php" method="post">
    <fieldset>
        <div class="form-group">
            <select class="form-control" name="sell_symbol">
                <option value=""> </option>
                <?php
                    $rows = $_SESSION["portfolio"];
                
                    foreach ($rows as $row)
                    {
                    print("<option value='{$row["symbol"]}'>{$row["symbol"]}</option>");
                    }
                
                ?>          
            </select>
        </div>
        <div class="form-group">
            <button type="submit" class="btn btn-default">Sell</button>
        </div>
    </fieldset>
</form>
