<script lang="ts">
    import Home from "./home.svelte";
    import TimetablePage from "./timetable-page.svelte";

    // Svelte 5 rune for reactive state
    let activeYear: number | null = $state(null);

    function navigateTo(year: number) {
        activeYear = year;
    }
</script>

<main class="min-h-auto bg-gray-50 text-black rounded-xl mt-5">
    {#if activeYear === null}
        <Home {navigateTo} />
    {:else}
        <TimetablePage year={activeYear} {navigateTo} />
    {/if}
</main>
