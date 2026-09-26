<script lang="ts">
    // Placeholder until the browser takes over: server-rendered (and printed) output must
    // not contain the build time, or every build would produce a different page.
    let time = $state("--:--:--");

    function formatTime(date: Date) {
        return [date.getHours(), date.getMinutes(), date.getSeconds()]
            .map((n) => String(n).padStart(2, "0"))
            .join(":");
    }

    // Browser only; the returned cleanup stops the timer when the demo unmounts.
    $effect(() => {
        time = formatTime(new Date());
        const id = setInterval(() => {
            time = formatTime(new Date());
        }, 1000);
        return () => clearInterval(id);
    });
</script>

<div
    class="min-h-auto text-black mt-5 rounded-xl bg-gray-900 p-6 flex flex-col items-center justify-center gap-4"
>
    <h1 class="text-2xl font-semibold text-gray-200">Live Clock</h1>
    <div
        class="text-4xl sm:text-6xl font-mono font-bold tracking-wider sm:tracking-widest text-cyan-400 drop-shadow-lg"
    >
        {time}
    </div>
    <p class="text-gray-400 text-sm">Updates every second via setInterval()</p>
</div>
