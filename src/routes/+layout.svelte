<script lang="ts">
    import { siteConfig } from "$lib/site-config";
    import { onMount } from "svelte";
    import "../app.css";
    import { useSiteConfig } from "@ethercorps/kit";

    let { children } = $props();

    useSiteConfig(() => siteConfig);
</script>

<svelte:head>
    <link rel="manifest" href="/manifest.json" />
</svelte:head>

{@render children?.()}
