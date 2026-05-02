<script lang="ts">
    import { Button } from "@ethercorps/kit";

    function printCurrentPage() {
        window.print();
    }
</script>

<div class="py-2 no-print w-full">
    <Button class="mt-2 w-full" onclick={printCurrentPage}>Print Page</Button>
</div>
