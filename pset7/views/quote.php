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