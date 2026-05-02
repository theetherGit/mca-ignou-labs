<script lang="ts">
    import { DocsLayout } from "@ethercorps/kit";
    import { navigation } from "$lib/navigation";

    let { children } = $props();
</script>

<DocsLayout {navigation}>
    {#snippet logo()}
        <img src="/logo-ethercorps.png" alt="Ethercorps Logo" class="size-8" />
        <span class="text-2xl font-bold">Syntax Lab</span>
    {/snippet}

    {@render children?.()}
</DocsLayout>
