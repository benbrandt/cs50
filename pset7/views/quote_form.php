<form action="quote.php" method="post">
    <fieldset>
        <div class="form-group">
            <input autocomplete="off" autofocus class="form-control" name="symbol" placeholder="Symbol" type="text"/>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">
                <span aria-hidden="true" class="glyphicon glyphicon-usd"></span>
                Get Quote
            </button>
        </div>
    </fieldset>
</form>

<?php if (isset($stock)): ?>
    <div class="alert alert-success" role="alert">
        <strong><?= htmlspecialchars($stock["symbol"]) ?></strong> 
        <?= htmlspecialchars($stock["name"]) ?> 
        <?= trim_zeroes($stock["price"]) ?>
    </div>
<?php endif ?>

<?php if (isset($error)): ?>
    <div class="alert alert-danger" role="alert"><?= htmlspecialchars($error) ?></div>
<?php endif ?>
